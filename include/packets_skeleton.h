#ifndef PACKETS_SKELETON_H
#define PACKETS_SKELETON_H

#include "../lib.h"


class packets_skeleton
{
    public:
        packets_skeleton();
        virtual ~packets_skeleton();

    private:


    public:
        static void print_packet(byte *raw, int len);
        void *keys_generator(unsigned char *key);
        void content_copy(unsigned char *dest,unsigned char *source,int source_lenght);





};

#endif // PACKETS_SKELETON_H
