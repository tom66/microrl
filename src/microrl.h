#ifndef _MICRORL_H_
#define _MICRORL_H_

#include "config.h"

#ifdef MICRORL_USE_HISTORY
// history struct, contain internal variable
// history store in static ring buffer for memory saving
typedef struct {
	char ring_buf [MICRORL_RING_HISTORY_LEN];
	int begin;
	int end;
	int cur;
} ring_history_t;
#endif

// microrl struct, contain internal library data
typedef struct {
#ifdef MICRORL_USE_ESC_SEQ
	char escape_seq;
	char escape;
#endif
#if (defined(MICRORL_ENDL_CRLF) || defined(MICRORL_ENDL_LFCR))
	char tmpch;
#endif
#ifdef MICRORL_USE_HISTORY
	ring_history_t ring_hist;          // history object
#endif
	char * prompt_str;                 // pointer to prompt string
	char cmdline [MICRORL_COMMAND_LINE_LEN];  // cmdline buffer
	int cmdlen;                        // last position in command line
	int cursor;                        // input cursor
	int (*execute) (int argc, const char * const * argv );            // ptr to 'execute' callback
	char ** (*get_completion) (int argc, const char * const * argv ); // ptr to 'completion' callback
	void (*print) (const char *);                                     // ptr to 'print' callback
#ifdef MICRORL_USE_CTRL_C
	void (*sigint) (void);
#endif
} microrl_t;

// init internal data, calls once at start up
void microrl_init (microrl_t * pThis, void (*print)(const char*));

// set echo mode (true/false), using for disabling echo for password input
// echo mode will enabled after user press Enter.
void microrl_set_echo (int);

// set pointer to callback complition func, that called when user press 'Tab'
// callback func description:
//   param: argc - argument count, argv - pointer array to token string
//   must return NULL-terminated string, contain complite variant splitted by 'Whitespace'
//   If complite token found, it's must contain only one token to be complitted
//   Empty string if complite not found, and multiple string if there are some token
void microrl_set_complete_callback (microrl_t * pThis, char ** (*get_completion)(int, const char* const*));

// pointer to callback func, that called when user press 'Enter'
// execute func param: argc - argument count, argv - pointer array to token string
void microrl_set_execute_callback (microrl_t * pThis, int (*execute)(int, const char* const*));

// set callback for Ctrl+C terminal signal
#ifdef MICRORL_USE_CTRL_C
void microrl_set_sigint_callback (microrl_t * pThis, void (*sigintf)(void));
#endif

// insert char to cmdline (for example call in usart RX interrupt)
void microrl_insert_char (microrl_t * pThis, int ch);

#endif
