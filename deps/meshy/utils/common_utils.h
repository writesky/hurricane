//
// Created by yankaixin on 2022/1/3.
//

#ifndef HURRICANE_COMMON_UTILS_H
#define HURRICANE_COMMON_UTILS_H
#ifndef NET_FRAMEWORK_COMMON_UTILS_H
#define NET_FRAMEWORK_COMMON_UTILS_H

#include <fcntl.h>
#include <cstdint>

namespace meshy {

    int32_t SetNonBlocking(int32_t sockfd);

}
#endif //HURRICANE_COMMON_UTILS_H
