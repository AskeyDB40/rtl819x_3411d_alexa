
#ifndef _MULTI_ROOM_INFO_H_
#define _MULTI_ROOM_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _multi_room_param multi_room_param_t;
struct _multi_room_param {
    int enable_multi_room;
    int channel_type;
    int slave_channel_type;
};

int is_multi_room_enabled();

#ifdef __cplusplus
}
#endif

#endif // _MULTI_ROOM_INFO_H_
