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

import time
from gnuradio import gr, gr_unittest
from gnuradio import blocks
import chat_blocks

class qa_chat_sanitizer (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_connect_blocks (self):
        """ Connect the sanitizer to the receiver """
        prefix = "UserName"
        sanitizer = chat_blocks.chat_sanitizer(prefix)
        receiver = chat_blocks.chat_receiver()
        self.tb.msg_connect(sanitizer, 'out', receiver, 'in')
        self.tb.start()
        msg1 = "Message1"
        msg2 = "Message2"
        print "This should print '[{}] {}':".format(prefix, msg1)
        sanitizer.post_message(msg1)
        print "This should print '[{}] {}':".format(prefix, msg2)
        sanitizer.post_message(msg2)
        self.tb.stop()
        self.tb.wait()
        print "(Sometimes, the messages won't show up... don't worry!)"

if __name__ == '__main__':
    gr_unittest.run(qa_chat_sanitizer, "qa_chat_sanitizer.xml")
