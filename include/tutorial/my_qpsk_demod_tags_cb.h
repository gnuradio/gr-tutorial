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

#ifndef INCLUDED_DEMOD_MY_QPSK_DEMOD_TAGS_CB_H
#define INCLUDED_DEMOD_MY_QPSK_DEMOD_TAGS_CB_H

#include <tutorial/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace tutorial {

    /*!
     * \brief A QPSK demodulator.
     * \ingroup tutorial
     *
     * Maps complex symbols to unpacked bytes.
     *
     * This demodulator understands two constellations:
     *
     * With Gray coding:
     *
     * <pre>
     * (1,0) | (0,0)
     * ------+------
     * (1,1) | (0,1)
     * </pre>
     *
     * Without Gray coding:
     *
     * <pre>
     * (1,0) | (0,0)
     * ------+------
     * (1,1) | (0,1)
     * </pre>
     *
     * This version also outputs tags if the amplitude drops below 0.01.
     */
    class TUTORIAL_API my_qpsk_demod_tags_cb : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<my_qpsk_demod_tags_cb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of demod::my_qpsk_demod_tags_cb.
       *
       * To avoid accidental use of raw pointers, demod::my_qpsk_demod_tags_cb's
       * constructor is in a private implementation
       * class. demod::my_qpsk_demod_tags_cb::make is the public interface for
       * creating new instances.
       *
       * \param gray_code Set to true to activate the Gray code.
       */
      static sptr make(bool gray_code);
    };

  } // namespace tutorial 
} // namespace gr

#endif /* INCLUDED_DEMOD_MY_QPSK_DEMOD_TAGS_CB_H */

