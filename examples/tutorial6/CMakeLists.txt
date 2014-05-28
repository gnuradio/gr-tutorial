########################################################################
# Install example files into examples/tutorials/tutorial6
########################################################################

file(GLOB grc_files "*.grc")
install(
    FILES ${grc_files}
    DESTINATION ${GR_PKG_TUTORIALS_EXAMPLES_DIR}/tutorial6
    COMPONENT "tutorials_python"
)
