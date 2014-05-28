########################################################################
# Install example files into examples/tutorials/tutorial7
########################################################################

file(GLOB grc_files "*.grc")
install(
    FILES ${grc_files}
    DESTINATION ${GR_PKG_TUTORIALS_EXAMPLES_DIR}/tutorial7
    COMPONENT "tutorials_python"
)
