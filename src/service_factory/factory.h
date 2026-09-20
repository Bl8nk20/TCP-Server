#ifndef FACTORY_H
#define FACTORY_H

#include ""

typedef enum{
    SERVICE_ECHO,
    SERVICE_UPPERCASE,
    SERIVCE_UNKNOWN
} ServiceType;

Command* service_factory_create(const unsigned char *buffer, size_t len)

#endif
