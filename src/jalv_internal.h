/*
  Copyright 2007-2011 David Robillard <http://drobilla.net>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef JALV_INTERNAL_H
#define JALV_INTERNAL_H

#include <semaphore.h>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include "lilv/lilv.h"

#include "suil/suil.h"

#include "symap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define JALV_UI_UPDATE_HZ 15

typedef struct {
	LilvWorld*         world;         /**< Lilv World */
	Symap*             symap;         /**< Symbol (URI) map */
	jack_client_t*     jack_client;   /**< Jack client */
	jack_ringbuffer_t* ui_events;     /**< Port events from UI */
	jack_ringbuffer_t* plugin_events; /**< Port events from plugin */
	sem_t*             done;          /**< Exit semaphore */
	const LilvPlugin*  plugin;        /**< Plugin class (RDF data) */
	const LilvUI*      ui;            /**< Plugin UI (RDF data) */
	LilvInstance*      instance;      /**< Plugin instance (shared library) */
	SuilInstance*      ui_instance;   /**< Plugin UI instance (shared library) */
	struct Port*       ports;         /**< Port array of size num_ports */
	uint32_t           num_ports;     /**< Size of the two following arrays: */
	jack_nframes_t     sample_rate;   /**< Sample rate */
	jack_nframes_t     event_delta_t; /**< Frames since last update sent to UI */
	LilvNode*          input_class;   /**< Input port class (URI) */
	LilvNode*          output_class;  /**< Output port class (URI) */
	LilvNode*          control_class; /**< Control port class (URI) */
	LilvNode*          audio_class;   /**< Audio port class (URI) */
	LilvNode*          event_class;   /**< Event port class (URI) */
	LilvNode*          midi_class;    /**< MIDI event class (URI) */
	LilvNode*          optional;      /**< lv2:connectionOptional port property */
	uint32_t           midi_event_id; /**< MIDI event class ID */
} Jalv;

void
jalv_init(int* argc, char*** argv);

LilvNode*
jalv_native_ui_type(Jalv* jalv);

int
jalv_open_ui(Jalv*         jalv,
             SuilInstance* instance);

bool
jalv_emit_ui_events(Jalv* jalv);

void
jalv_save(Jalv* jalv, const char* dir);

void
jalv_restore(Jalv* jalv, const char* dir);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // JALV_INTERNAL_H
