CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#--------------------------------------------------
# Find and Use ParaView
#--------------------------------------------------
FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})
 ADD_PARAVIEW_PLUGIN(SymToGenMatrixFilter "1.0" 
   SERVER_MANAGER_XML vtkSymToGenMatrixFilter_SM.xml
   SERVER_MANAGER_SOURCES vtkSymToGenMatrixFilter.cxx
   REQUIRED_ON_SERVER)

# let cmake decide which c++-version is needed to satisfy all the features used in the source-code
target_compile_features(SymToGenMatrixFilter PRIVATE cxx_range_for)
