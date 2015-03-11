AUX_SOURCE_DIRECTORY(. DIR)
ADD_LIBRARY(classifier OBJECT ${DIR})
include_directories( "../../itrbase")