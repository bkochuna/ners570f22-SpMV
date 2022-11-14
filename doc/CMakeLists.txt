find_package(Doxygen)

if(DOXYGEN_FOUND)
  MESSAGE(STATUS "Processing Doxygen Documentation")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in
	         ${CMAKE_CURRENT_BINARY_DIR}/doxy.config
		)
  add_custom_target(docs
      COMMAND ${DOXYGEN_EXECUTABLE} doxy.config
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      )
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
          DESTINATION doc)
else()
  MESSAGE(STATUS "Skipping Doxygen documentation processing...")
endif()
