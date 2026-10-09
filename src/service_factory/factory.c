#include <string.h>
#include "factory.h"
#include "services.h"

static ServiceType parse_service_type(const unsigned char *buffer, size_t len){
    if(buffer == NULL || len == 0){
        return SERVICE_UNKNOWN;
    }

    if(len >= 4 && memcmp(buffer, "ECHO",4) == 0){
        return SERVICE_ECHO;
    }
    if (len >= 5 && memcmp(buffer, "UPPER", 5) == 0) {
        return SERVICE_UPPERCASE;
    }

    return SERVICE_UNKNOWN;
}

Command* service_factory_create(const unsigned char *buffer, size_t len){
    ServiceType type = parse_service_type(buffer, len);

    switch (type) {
        case SERVICE_ECHO:
            return create_echo_command();
        case SERVICE_UPPERCASE:
            return create_uppercase_command();
        case SERVICE_UNKNOWN:
        default:
            return NULL;
    }}
