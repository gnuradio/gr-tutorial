########################################################################
# Install example files into examples/tutorials/tutorial3
########################################################################

file(GLOB grc_files "*.grc")
install(
    FILES ${grc_files}
    DESTINATION ${GR_PKG_TUTORIALS_EXAMPLES_DIR}/tutorial3
    COMPONENT "tutorials_python"
)
