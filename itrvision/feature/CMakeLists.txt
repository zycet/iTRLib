AUX_SOURCE_DIRECTORY(. DIR)
ADD_LIBRARY(feature OBJECT ${DIR})

include_directories( "../../itrbase")
include_directories( "../../itralgorithm")
include_directories( "../../3rdparty/alglib")