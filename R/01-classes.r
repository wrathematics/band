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
#' @export
setClass(
  Class="GenBandMat", 
  representation=representation(
    Data="numeric",
    dim="integer",
    kl="integer",
    ku="integer"
  ),
  
  prototype=prototype(
    Data=numeric(0),
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
#' @export
setClass(
  Class="SymBandMat", 
  representation=representation(
    Data="numeric",
    dim="integer",
    k="integer"
  ),
  
  prototype=prototype(
    Data=numeric(0),
    dim=c(0L, 0L),
    k=0L
  ),
  
  validity=valid.SymBandMat
)



setClassUnion("BandMat", c("GenBandMat", "SymBandMat"))
