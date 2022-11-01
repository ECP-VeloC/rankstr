###############
# Build tests
###############

################
# Add tests to ctest
################

IF(RANKSTR_LINK_STATIC)
   SET(rankstr_lib rankstr::rankstr-static)
ELSE()
   SET(rankstr_lib rankstr::rankstr)
ENDIF()

ADD_EXECUTABLE(rankstr_test test_rankstr.c)
TARGET_LINK_LIBRARIES(rankstr_test ${rankstr_lib})
RANKSTR_ADD_TEST(rankstr_test 256 "")
#ADD_TEST(NAME rankstr_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3 ./rankstr_test)

####################
# make a verbose "test" target named "check"
####################

ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
