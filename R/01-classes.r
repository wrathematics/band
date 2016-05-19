# http://www.netlib.org/lapack/lug/node124.html

setClassUnion("Linalg", c("vector", "matrix"))

#' Banded Matrix Classes
#' 
#' Class for general and symmetric banded matrices.
#' 
#' @slot DATA
#' The data.
#' @slot dim
#' matrix dimension.
#' @slot kl,ku
#' Size of the upper and lower bands.
#' 
#' @name classes
#' @rdname classes
#' @keywords Classes
#' @docType class
setClass(
  Class="GenBandMat", 
  representation=representation(
    Data="matrix",
    dim="integer",
    kl="integer",
    ku="integer"
  ),
  
  prototype=prototype(
    Data=matrix(nrow=0, ncol=0),
    dim=c(1L, 1L),
    kl=0L,
    ku=0L
  ),
  
  validity=valid.GenBandMat
)

#' @slot k
#' Size of the bands in the symmetric case.
#' 
#' @rdname classes
setClass(
  Class="SymBandMat", 
  representation=representation(
    Data="matrix",
    dim="integer",
    k="integer"
  ),
  
  prototype=prototype(
    Data=matrix(nrow=0, ncol=0),
    dim=c(0L, 0L),
    k=0L
  ),
  
  validity=valid.SymBandMat,
  
  contains="GenBandMat"
)
