/* -*- c++ -*- */
/*
 * Copyright 2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "my_qpsk_demod_tags_cb_impl.h"
#include <gnuradio/math.h>
#include <gnuradio/gr_complex.h>

namespace gr {
  namespace tutorial {

    my_qpsk_demod_tags_cb::sptr
    my_qpsk_demod_tags_cb::make(bool gray_code)
    {
      return gnuradio::get_initial_sptr
        (new my_qpsk_demod_tags_cb_impl(gray_code));
    }

    /*
     * The private constructor
     */
    my_qpsk_demod_tags_cb_impl::my_qpsk_demod_tags_cb_impl(bool gray_code)
      : gr::block("my_qpsk_demod_tags_cb",
                  gr::io_signature::make(1, 1, sizeof(gr_complex)),
                  gr::io_signature::make(1, 1, sizeof(unsigned char))),
        d_gray_code(gray_code),
	d_low_ampl_state(false)
    {
      if (gray_code) {
	GR_LOG_DEBUG(d_debug_logger, "Gray code enabled.");
      } else {
	GR_LOG_DEBUG(d_debug_logger, "Gray code disabled.");
      }
    }

    /*
     * Our virtual destructor.
     */
    my_qpsk_demod_tags_cb_impl::~my_qpsk_demod_tags_cb_impl()
    {
    }

    void
    my_qpsk_demod_tags_cb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        // We need the same number of outputs as we need inputs
	unsigned int input_required = noutput_items;

      	unsigned ninputs = ninput_items_required.size();
      	for(unsigned int i = 0; i < ninputs; i++)
       	    ninput_items_required[i] = input_required;
    }

    int
    my_qpsk_demod_tags_cb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

	// Perform ML decoding over the input iq data to generate alphabets
        for(int i = 0; i < noutput_items; i++) {
	  // ML decoder, determine the minimum distance from all constellation points
	  out[i] = get_minimum_distances(in[i]);
	  if (std::abs(in[i]) < 0.01 and not d_low_ampl_state) {
	    add_item_tag(0, // Port number
		nitems_written(0) + i, // Offset
		pmt::mp("amplitude_warning"), // Key
		pmt::from_double(std::abs(in[i])) // Value
		);
	    d_low_ampl_state = true;
	  }
	  else if (std::abs(in[i]) >= 0.01 and d_low_ampl_state) {
	    add_item_tag(0, // Port number
		nitems_written(0) + i, // Offset
		pmt::mp("amplitude_recovered"), // Key
		pmt::PMT_T // Value
		);
	    d_low_ampl_state = false; // Reset state
	  }
      	}

	// Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

    unsigned char
    my_qpsk_demod_tags_cb_impl::get_minimum_distances(const gr_complex &sample)
    {
      if (d_gray_code) {
	unsigned char bit0 = 0;
	unsigned char bit1 = 0;
	// The two left quadrants (quadrature component < 0) have this bit set to 1
	if (sample.imag() < 0) {
	  bit0 = 0x01;
	}
	// The two lower quadrants (in-phase component < 0) have this bit set to 1
	if (sample.real() < 0) {
	  bit1 = 0x01 << 1;
	}
	return bit0 | bit1;
      } else {
	// For non-gray code, we can't simply decide on signs, so we check every single quadrant.
	if (sample.imag() >= 0 and sample.real() >= 0) {
	  return 0x00;
	}
	else if (sample.imag() >= 0 and sample.real() < 0) {
	  return 0x01;
	}
	else if (sample.imag() < 0 and sample.real() < 0) {
	  return 0x02;
	}
	else if (sample.imag() < 0 and sample.real() >= 0) {
	  return 0x03;
	}
      }
    }

  } /* namespace tutorial */
} /* namespace gr */
