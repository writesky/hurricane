
#include "../../../../include/hurricane/Hurricane.h"
#include "../../../../include/hurricane/message/Message.h"
#include "../../../../include/hurricane/message/MessageLoop.h"

#include <Windows.h>

namespace hurricane {
    namespace message {
        MessageLoop::MessageLoop() {
            _threadId = GetCurrentThreadId();
        }

        void MessageLoop::Run() {
            MSG msg;

            while ( GetMessage(&msg, 0, 0, 0) ) {
                auto handler = _messageHandlers.find(msg.message);

                if ( handler != _messageHandlers.end() ) {
                    handler->second((Message*)(msg.wParam));
                }

                DispatchMessage(&msg);

                if ( msg.message == Message::Type::Stop ) {
                    break;
                }
            }
        }

        void MessageLoop::PostMessage(Message* message) {
            PostThreadMessage(_threadId, message->GetType(), WPARAM(message), 0);
        }

        void MessageLoop::Stop() {
            PostMessage(new Message(Message::Type::Stop));
        }
    }
}