########################################################################
# Install example files into examples/tutorials/tutorial7
########################################################################

install(
    FILES
    mpsk_rrc_rolloff.grc
    mpsk_stage1.grc
    mpsk_stage2.grc
    mpsk_stage3.grc
    mpsk_stage4.grc
    mpsk_stage5.grc
    mpsk_stage6.grc
    multipath_sim.grc
    symbol_sampling.grc
    symbol_differntial_filter.grc
    symbol_differntial_filter_phases.grc
    symbol_sampling_diff.grc
    DESTINATION ${GR_PKG_TUTORIALS_EXAMPLES_DIR}/tutorial7
    COMPONENT "tutorials_python"
)
