/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */


#ifndef _IOTX_CM_INTERNAL_H_
#define _IOTX_CM_INTERNAL_H_

#include "iotx_alink_internal.h"
#include "alink_wrapper.h"
#include "mqtt_api.h"


#ifdef INFRA_MEM_STATS
#include "infra_mem_stats.h"
#define cm_malloc(size)              LITE_malloc(size, MEM_MAGIC, "dm")
#define cm_free(ptr)                 LITE_free(ptr)
#else
#define cm_malloc(size)              HAL_Malloc(size)
#define cm_free(ptr)                 {HAL_Free((void *)ptr);ptr = NULL;}
#endif


#ifdef INFRA_LOG
#include "infra_log.h"
#define cm_emerg(...)                log_emerg("ALINK", __VA_ARGS__)
#define cm_crit(...)                 log_crit("ALINK", __VA_ARGS__)
#define cm_err(...)                  log_err("ALINK", __VA_ARGS__)
#define cm_warning(...)              log_warning("ALINK", __VA_ARGS__)
#define cm_info(...)                 log_info("ALINK", __VA_ARGS__)
#define cm_debug(...)                log_debug("ALINK", __VA_ARGS__)
#else
#define cm_emerg(...)                do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#define cm_crit(...)                 do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#define cm_err(...)                  do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#define cm_warning(...)              do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#define cm_info(...)                 do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#define cm_debug(...)                do{HAL_Printf(__VA_ARGS__);HAL_Printf("\r\n");}while(0)
#endif

typedef int (*iotx_cm_connect_fp)(uint32_t timeout);
typedef int (*iotx_cm_yield_fp)(unsigned int timeout);
typedef int (*iotx_cm_sub_fp)(iotx_cm_ext_params_t *params, const char *topic,
                              iotx_cm_data_handle_cb topic_handle_func, void *pcontext);
typedef int (*iotx_cm_unsub_fp)(const char *topic);
typedef int (*iotx_cm_pub_fp)(iotx_cm_ext_params_t *params, const char *topic, const char *payload,
                              unsigned int payload_len);
typedef int (*iotx_cm_close_fp)();


typedef struct iotx_connection_st {
    int                              fd;
    void                             *open_params;
    void                             *context;
    void                             *list_lock;
    iotx_cm_protocol_types_t         protocol_type;
    iotx_cm_connect_fp               connect_func;
    iotx_cm_sub_fp                   sub_func;
    iotx_cm_unsub_fp                 unsub_func;
    iotx_cm_pub_fp                   pub_func;
    iotx_cm_yield_fp                 yield_func;
    iotx_cm_close_fp                 close_func;
    iotx_cm_event_handle_cb          event_handler;
    void                             *cb_data;

} iotx_cm_connection_t;

extern const char ERR_INVALID_PARAMS[];
#endif /* _LINKKIT_CM_H_ */

