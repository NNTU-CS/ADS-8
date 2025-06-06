install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")

file(COPY ${PROJECT_SOURCE_DIR}/src/war_peace.txt DESTINATION "/home/runner/work/ADS-8/ADS-8/build/test")
