#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Fri May 30 05:41:08 2014
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import constsink_gl
from gnuradio.wxgui import forms
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import numpy
import tutorial
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.noise_amplitude = noise_amplitude = .01

        ##################################################
        # Blocks
        ##################################################
        _noise_amplitude_sizer = wx.BoxSizer(wx.VERTICAL)
        self._noise_amplitude_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_noise_amplitude_sizer,
        	value=self.noise_amplitude,
        	callback=self.set_noise_amplitude,
        	label='noise_amplitude',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._noise_amplitude_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_noise_amplitude_sizer,
        	value=self.noise_amplitude,
        	callback=self.set_noise_amplitude,
        	minimum=0,
        	maximum=1,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_noise_amplitude_sizer)
        self.wxgui_constellationsink2_0 = constsink_gl.const_sink_c(
        	self.GetWin(),
        	title="Constellation Plot",
        	sample_rate=samp_rate,
        	frame_rate=5,
        	const_size=2048,
        	M=4,
        	theta=0,
        	loop_bw=6.28/100.0,
        	fmax=0.06,
        	mu=0.5,
        	gain_mu=0.005,
        	symbol_rate=samp_rate/2.,
        	omega_limit=0.005,
        )
        self.Add(self.wxgui_constellationsink2_0.win)
        self.tutorial_my_qpsk_demod_cb_0 = tutorial.my_qpsk_demod_cb(True)
        self.digital_psk_mod_0 = digital.psk.psk_mod(
          constellation_points=4,
          mod_code="gray",
          differential=True,
          samples_per_symbol=2,
          excess_bw=.35,
          verbose=False,
          log=False,
          )
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_head_0 = blocks.head(gr.sizeof_char*1, 100)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, "./examples/qpsk_demod_sink.dat", False)
        self.blocks_file_sink_0.set_unbuffered(True)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 4, 10000)), True)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, noise_amplitude, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.digital_psk_mod_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.blocks_head_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.analog_random_source_x_0, 0), (self.digital_psk_mod_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.wxgui_constellationsink2_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.tutorial_my_qpsk_demod_cb_0, 0))
        self.connect((self.tutorial_my_qpsk_demod_cb_0, 0), (self.blocks_head_0, 0))


# QT sink close method reimplementation

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.wxgui_constellationsink2_0.set_sample_rate(self.samp_rate)

    def get_noise_amplitude(self):
        return self.noise_amplitude

    def set_noise_amplitude(self, noise_amplitude):
        self.noise_amplitude = noise_amplitude
        self._noise_amplitude_slider.set_value(self.noise_amplitude)
        self._noise_amplitude_text_box.set_value(self.noise_amplitude)
        self.analog_noise_source_x_0.set_amplitude(self.noise_amplitude)

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()

