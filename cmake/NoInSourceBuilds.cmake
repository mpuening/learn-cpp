#
# Prevent In-source builds in project
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "\n\nIn-source builds are not allowed in this project.\n\n")
endif()
