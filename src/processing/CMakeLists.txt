# src/processing/CMakeLists.txt

project (processing)

# Adding library with the corresponding sources (static library)

add_library (${PROJECT_NAME} 
	     arrayuts.c
	     ephem.c
    	     inputs.c
             keplerian.c
             lambert.c
             matrixops.c
             postprocess.c
             process.c
             rootFinding.c
)

add_library (proc::lib ALIAS ${PROJECT_NAME})


target_include_directories (${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}
)



