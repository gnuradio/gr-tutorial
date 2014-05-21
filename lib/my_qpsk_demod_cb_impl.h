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

#ifndef INCLUDED_DEMOD_MY_QPSK_DEMOD_CB_IMPL_H
#define INCLUDED_DEMOD_MY_QPSK_DEMOD_CB_IMPL_H

#include <tutorial/my_qpsk_demod_cb.h>
#include <stdlib.h>
#include <float.h>

namespace gr {
  namespace tutorial {

    class my_qpsk_demod_cb_impl : public my_qpsk_demod_cb
    {
     private:
      bool d_differential_coding; 
      bool d_Gray_code;	     

     public:
      my_qpsk_demod_cb_impl(bool differential_coding, bool Gray_code);
      ~my_qpsk_demod_cb_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
      unsigned char get_minimum_distances(const gr_complex *sample);
      float get_euclidean_distance(gr_complex *d1, const gr_complex *d2);
      };

  } // namespace tutorial 
} // namespace gr

#endif /* INCLUDED_DEMOD_MY_QPSK_DEMOD_CB_IMPL_H */

