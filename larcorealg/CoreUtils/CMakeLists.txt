cet_make_library(
         SOURCE DebugUtils.cxx
         LIBRARIES
           cetlib::cetlib
           cetlib_except::cetlib_except
        )

install_headers()
install_source()
