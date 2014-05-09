/* -*- c++ -*- */
/*
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "my_qpsk_demod_cb_impl.h"
#include <gnuradio/math.h>
#include <gnuradio/gr_complex.h>
#include <stdio.h>

namespace gr {
  namespace tutorial {

    #define SQRT_TWO 0.707107
    #define INFTY 1000
//    #define DEBUG

    my_qpsk_demod_cb::sptr
    my_qpsk_demod_cb::make(bool differential_coding, bool Gray_code)
    {
      return gnuradio::get_initial_sptr
        (new my_qpsk_demod_cb_impl(differential_coding, Gray_code));
    }

    /*
     * The private constructor
     */
    my_qpsk_demod_cb_impl::my_qpsk_demod_cb_impl(bool differential_coding, bool Gray_code)
      : gr::block("my_qpsk_demod_cb",
                  gr::io_signature::make(1, 1, sizeof(gr_complex)),
                  gr::io_signature::make(1, 1, sizeof(unsigned char))),
        d_differential_coding(differential_coding),
        d_Gray_code(Gray_code)
    {}

    /*
     * Our virtual destructor.
     */
    my_qpsk_demod_cb_impl::~my_qpsk_demod_cb_impl()
    {
    }

    void
    my_qpsk_demod_cb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	unsigned int input_required = noutput_items;

      	unsigned ninputs = ninput_items_required.size();
      	for(unsigned int i = 0; i < ninputs; i++)
       	    ninput_items_required[i] = input_required;
    }

    int
    my_qpsk_demod_cb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];
	gr_complex origin = gr_complex(0,0);
        // Perform ML decoding over the input iq data to generate alphabets
        for(int i = 0; i < noutput_items; i++)
	{
		// ML decoder, determine the minimum distance from all constellation points
		out[i] = get_minimum_distances(&(in[i]));
      	}

	// Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

    unsigned char
    my_qpsk_demod_cb_impl::get_minimum_distances(const gr_complex *sample)
    {
	unsigned char index, k;
	std::vector<float> s(3,0);
        gr_complex const_pt;
	float min_distance = INFTY;
	for(k = 0; k < 4; k++)
	{
	    if (d_Gray_code ==  true)
	    {
#ifdef DEBUG
		printf("Gray Code is enabled\n");
#endif
	   	switch(k)
	    	{
                    case 0:
		    {
		    	// (0,1)
			const_pt = gr_complex(SQRT_TWO, -SQRT_TWO);
		        break;
	            }
		    case 1:
	  	    {
		        // (1,1)
		   	const_pt = gr_complex(-SQRT_TWO, -SQRT_TWO);
		   	break;
		    }
	   	    case 2:
		    {
		        // (1,0)
		    	const_pt = gr_complex(-SQRT_TWO, SQRT_TWO);
		  	break;
		    }
		    case 3:
	  	    {
		    	// (0,0)
		   	const_pt = gr_complex(SQRT_TWO, SQRT_TWO);
		   	break;
		    }
		    default:
			printf("Invalid option\n");
	        }
	    }
	    else
	    {
#ifdef DEBUG
		printf("Gray Code is disabled\n");
#endif
	   	switch(k)
	    	{
		    case 0:
		    {
		    	// (0,1)
			const_pt = gr_complex(SQRT_TWO, -SQRT_TWO);
		        break;
	            }
		    case 1:
	  	    {
		        // (1,1)
		   	const_pt = gr_complex(-SQRT_TWO, -SQRT_TWO);
		   	break;
		    }
	   	    case 2:
		    {
		        // (1,0)
		    	const_pt = gr_complex(-SQRT_TWO, SQRT_TWO);
		  	break;
		    }
		    case 3:
	  	    {
		    	// (0,0)
		   	const_pt = gr_complex(SQRT_TWO, SQRT_TWO);
		   	break;
		    }
		    default:
			printf("Invalid option\n");
	        }
	    }
	    s[k] = get_euclidean_distance(&const_pt, sample);
         }

         // Mapping back the symbols to bytes
	 for (k = 0; k < 4 ; k++)
	 {
	     if (s[k] < min_distance)
	     {
	         min_distance = s[k];
		 index = k;
		 //printf("alphabet = %u \n",index);
 	     }
	 }
	 return index;
    }

    float
    my_qpsk_demod_cb_impl::get_euclidean_distance(gr_complex *d1, const gr_complex *d2)
    {
    	return ((d1->real() - d2->real()) * (d1->real() - d2->real()) +  ((d1->imag() - d2->imag()) * (d1->imag() - d2->imag())));
    }
  } /* namespace tutorialtutorial  */
} /* namespace gr */
