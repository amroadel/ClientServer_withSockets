#include "message.h"
#include <cctype>
#include <cstring>

Message::Message(int operation, void *p_message, size_t p_message_size, int p_rpc_id)
{
    this->operation = operation;
    this->message = p_message;
    this->message_size = p_message_size;
    this->rpc_id = p_rpc_id;
}

inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

Message::Message(char *marshalled_base64, size_t marshalled_base64_size)
{
    size_t s = marshalled_base64_size;
    int i = 0;
    int j = 0;
    int k = 0;
    int in_ = 0;
    unsigned char sixtets[4], octets[3];
    size_t s2 = (s / 4) * 3;
    char *ret = new char[s2];

    while (s-- && (marshalled_base64[in_] != '=') && is_base64(marshalled_base64[in_]))
    {
        sixtets[i++] = marshalled_base64[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                sixtets[i] = strchr(base64_chars, sixtets[i]) - base64_chars;

            octets[0] = (sixtets[0] << 2) + ((sixtets[1] & 0x30) >> 4);
            octets[1] = ((sixtets[1] & 0xf) << 4) + ((sixtets[2] & 0x3c) >> 2);
            octets[2] = ((sixtets[2] & 0x3) << 6) + sixtets[3];

            for (i = 0; (i < 3); i++)
                ret[k++] = octets[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 4; j++)
            sixtets[j] = 0;

        for (j = 0; j < 4; j++)
            sixtets[j] = strchr(base64_chars, sixtets[j]) - base64_chars;

        octets[0] = (sixtets[0] << 2) + ((sixtets[1] & 0x30) >> 4);
        octets[1] = ((sixtets[1] & 0xf) << 4) + ((sixtets[2] & 0x3c) >> 2);
        octets[2] = ((sixtets[2] & 0x3) << 6) + sixtets[3];

        for (j = 0; (j < i - 1); j++)
            ret[k++] = octets[j];
    }

    this->operation = 0;
    this->message = ret;
    this->message_size = k;
    this->rpc_id = 0;
}

char *Message::marshal()
{
    int i = 0;
    int j = 0;
    int k = 0;
    unsigned char octets[3], sixtets[4];
    size_t s = message_size;
    char *m = (char *)message;
    size_t s2 = (s / 3) * 4;
    s2 = (s % 3) ? s2 + 1 : s2;
    char *ret = new char[s2];

    while (s--)
    {
        octets[i++] = *(m++);
        if (i == 3)
        {
            sixtets[0] = (octets[0] & 0xfc) >> 2;
            sixtets[1] = ((octets[0] & 0x03) << 4) + ((octets[1] & 0xf0) >> 4);
            sixtets[2] = ((octets[1] & 0x0f) << 2) + ((octets[2] & 0xc0) >> 6);
            sixtets[3] = octets[2] & 0x3f;

            for (i = 0; i < 4; i++)
                ret[k++] = base64_chars[sixtets[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            octets[j] = '\0';

        sixtets[0] = (octets[0] & 0xfc) >> 2;
        sixtets[1] = ((octets[0] & 0x03) << 4) + ((octets[1] & 0xf0) >> 4);
        sixtets[2] = ((octets[1] & 0x0f) << 2) + ((octets[2] & 0xc0) >> 6);
        sixtets[3] = octets[2] & 0x3f;

        for (j = 0; j < i + 1; j++)
            ret[k++] = base64_chars[sixtets[j]];

        while (i++ < 3)
            ret[k++] = '=';
    }

    return ret;
}

int Message::getOperation()
{
    return (this->operation);
}

int Message::getRPCId()
{
    return (this->rpc_id);
}

void *Message::getMessage()
{
    return (this->message);
}

size_t Message::getMessageSize()
{
    return (this->message_size);
}

MessageType Message::getMessageType()
{
    return (this->message_type);
}

void Message::setOperation(int _operation)
{
    this->operation = operation;
}

void Message::setMessage(void *message, size_t message_size)
{
    this->message = message;
    this->message_size = message_size;
}

void Message::setMessageType(MessageType message_type)
{
    this->message_type = message_type;
}

Message::~Message()
{
}
