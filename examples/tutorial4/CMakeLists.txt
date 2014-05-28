########################################################################
# Install example files into examples/tutorials/tutorial4
########################################################################

file(GLOB grc_files "*.grc")
install(
    FILES ${grc_files}
    DESTINATION ${GR_PKG_TUTORIALS_EXAMPLES_DIR}/tutorial4
    COMPONENT "tutorials_python"
)
