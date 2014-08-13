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

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from multiply_py_ff import multiply_py_ff

class qa_multiply_py_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        src_data = (0, 1, -2, 5.5, -0.5)
        expected_result = (0, 2, -4, 11, -1)
        src = blocks.vector_source_f (src_data)
        mult = multiply_py_ff (2)
        snk = blocks.vector_sink_f ()
        self.tb.connect (src, mult)
        self.tb.connect (mult, snk)
        self.tb.run ()
        result_data = snk.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data, 6)


if __name__ == '__main__':
    gr_unittest.run(qa_multiply_py_ff, "qa_multiply_py_ff.xml")
