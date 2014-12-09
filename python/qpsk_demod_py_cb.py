#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2014 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

import numpy
from gnuradio import gr

class qpsk_demod_py_cb(gr.sync_block):
    """
    docstring for block qpsk_demod_py_cb
    """
    def __init__(self, gray_code):
        gr.sync_block.__init__(self,
            name="qpsk_demod_py_cb",
            in_sig=[numpy.complex64],
            out_sig=[numpy.uint8])
        self.gray_code = gray_code

    def get_minimum_distances(self, sample):
        if self.gray_code == 1:
            if (sample.imag >= 0 and sample.real >= 0):
                return 0 # 1+1j
            elif (sample.imag >= 0 and sample.real < 0):
                return 2 # -1+1j
            elif (sample.imag < 0 and sample.real < 0):
                return 3 # -1-1j
            elif (sample.imag < 0 and sample.real >= 0):
                return 1 # 1-1j
        else:
            if (sample.imag >= 0 and sample.real >= 0):
                return 0 # 1+1j
            elif (sample.imag >= 0 and sample.real < 0):
                return 3 # -1+1j
            elif (sample.imag < 0 and sample.real < 0):
                return 2 # -1-1j
            elif (sample.imag < 0 and sample.real >= 0):
                return 1 # 1-1j

    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        
        for i in range(0, len(in0)):
            sample = in0[i]
            out[i] = self.get_minimum_distances(sample)
           
        return len(output_items[0])

