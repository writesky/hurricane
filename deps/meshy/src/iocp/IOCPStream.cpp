
#include "../../iocp/IOCPStream.h"
#include "../../utils/logger.h"

namespace meshy{
    int32_t IOCPStream::Receive(char *buffer, int32_t bufferSize, int32_t &readSize) {
        // IOCP already handled data reading out, leave this function blank.
        return 0;
    }

    int32_t IOCPStream::Send(const ByteArray &byteArray) {
        return send(GetNativeSocket(),byteArray.data(),byteArray.size(),0);
    }

    HANDLE IOCP::GetCompletionPort() {
        HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);  //window的API创建端口
        if (nullptr == completionPort) {
            TRACE_ERROR("CreateIoCompletionPort failed. Error:" + GetLastError());
            throw std::exception("CreateIoCompletionPort failed.");
        }

        return completionPort;
    }

    IOCP::OperationDataPtr IOCP::CreatOperationData(IOCPStreamPtr stream, int completionPort) {
        // Begin to process I/O using overlapped I/O
        // Post one or many WSARecv or WSASend requests to the new socket
        // Worker thread will serve the I/O request after the I/O request finished.
        IOCP::OperationData* perIOData = new IOCP::OperationData();
        perIOData->stream = stream.get();

        // Relate the socket to CompletionPort
        CreateIoCompletionPort((HANDLE)(perIOData->stream->GetNativeSocket()),
                               completionPort, (ULONG_PTR)perIOData->stream->GetNativeSocket(), 0);

        ZeroMemory(&(perIOData->overlapped), sizeof(OVERLAPPED));
        perIOData->databuff.len = BUFSIZ;
        perIOData->databuff.buf = perIOData->buffer;
        perIOData->operationType = IOCP::OperationType::Read;

        return IOCP::OperationDataPtr(perIOData);
    }

    void IOCP::ResetOperationData(OperationData *perIOData) {
        // Create single I/O operation data for next overlapped invoking.
        ZeroMemory(&(perIOData->overlapped), sizeof(OVERLAPPED));  //清空结构体
        perIOData->databuff.len = BUFSIZ;  //指定io数据缓存区长度及缓存区指针
        perIOData->databuff.buf = perIOData->buffer;
        perIOData->operationType = 0;
    }
}