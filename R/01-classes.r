setClassUnion("Linalg", c("vector", "matrix"))

setClassUnion("VecTypes", c("numeric", "logical"))


#' Banded Matrix Classes
#' 
#' Class for general and symmetric banded matrices.
#' 
#' @slot DATA
#' The data.
#' @slot dim
#' matrix dimension.
#' @slot kl,ku
#' Size of the upper and lower bands (bandwidth) in the general case.
#' 
#' @name classes
#' @aliases classes
#' @keywords Classes
#' @docType class
#' @rdname classes
NULL



#' @rdname classes
#' @export
setClass(
  Class="GenBandMat", 
  representation=representation(
    Data="VecTypes",
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
    Data="VecTypes",
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



#' @rdname classes
#' @export
setClass(
  Class="DiagMat", 
  representation=representation(
    Data="VecTypes",
    dim="integer"
  ),
  
  prototype=prototype(
    Data=numeric(0),
    dim=c(1L, 1L)
  ),
  
  validity=valid.DiagMat
)



#' @rdname classes
#' @export
setClass(
  Class="ZeroMat", 
  representation=representation(
    dim="integer"
  ),
  
  prototype=prototype(
    dim=c(1L, 1L)
  ),
  
  validity=valid.ZeroMat
)



setClassUnion("BandMat", c("ZeroMat", "DiagMat", "GenBandMat", "SymBandMat"))
