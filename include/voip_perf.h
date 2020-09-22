#ifndef __VOIP_PERF_H__
#define __VOIP_PERF_H__

typedef struct  {
	int32_t min;
	int32_t max;
	//float current; // Current value, may not be computed yet
	float average; // average for N-1
	float stdev;   // last standard deviation
	float last_q;  // q for N-1
	int32_t count;
	//float recent_average;
	//float first_average;
} voip_perf_metric_t;

typedef struct responses {
	int code;
	pj_str_t reason;
	int prob; // probability in percentage
} responses_t;



struct srv_state {
	unsigned stateless_cnt;
	unsigned stateful_cnt;
	unsigned call_cnt;
};

typedef struct cps_period {
	pj_time_val start;      // start ts of the period
	pj_time_val last_sleep; // ms when we last waited, to double check if we where interupted
	int call_count_ms;      // call count in the current ms
	int call_count;         // call count in the current period
	float cps;              // target cps, fixed
	float cpms;             // current target call per ms, adjusted frequently
} cps_period_t;

typedef struct extra_header {
	pj_str_t name;
	pj_str_t value;
} extra_header_t;

extra_header_t * load_json_config_extra_headers(json_t *extra_headers_json, int *extra_headers_count);
void print_detailed_response_code_received();

typedef struct user {
	pj_str_t ruri; // the RURI used when calling with this user
	pj_str_t furi;
	extra_header_t *headers;
	int headers_count;
} user_t;

#endif
