###############
# Build tests
###############


################
# Add tests to ctest
################

ADD_EXECUTABLE(rankstr_test test_rankstr.c)
TARGET_LINK_LIBRARIES(rankstr_test ${RANKSTR_EXTERNAL_LIBS} rankstr)
ADD_TEST(NAME rankstr_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3 ./rankstr_test)


####################
# make a verbose "test" target named "check"
####################

ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
