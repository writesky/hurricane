//
// Created by yankaixin on 2021/12/25.
//

#ifndef HURRICANE_LOOP_H
#define HURRICANE_LOOP_H

#pragma once

namespace meshy{

    class Loop{
    public:
        virtual ~Loop();

        void Start(){
            _Run();
        }

    protected:
        virtual void _Run()=0;
    };
}
#endif //HURRICANE_LOOP_H
