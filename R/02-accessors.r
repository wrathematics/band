#' getData
#' 
#' Extract the internal storage representation of the banded matrix. WARNING:
#' for advanced users only.
#' 
#' @details
#' See url in the references for an explanation of the storage.
#' 
#' @param x
#' A band matrix.
#' 
#' @references \url{http://www.netlib.org/lapack/lug/node124.html}
#' @keywords Accessors
#' @export
getData <- function(x) x@Data



#' getdim
#' 
#' Get the dimension of the banded matrix. Like \code{dim()} for R matrices.
#' 
#' @param x
#' A band matrix.
#' 
#' @keywords Accessors
#' @export
getdim <- function(x) x@dim



#' kdim
#' 
#' Get the "dimension" of the bands, i.e. the bandwidth.
#' 
#' @details
#' The first digit is the width of the lower band while the second is the
#' width of the upper band.  For a general band matrix, these numbers can
#' be different.  For a symmetric matrix, they will be the same.  For a
#' diagonal matrix, they will both be 0.  In any case, each will be a
#' non-negative integer.
#' 
#' @param x
#' A band matrix.
#' 
#' @return
#' A length 2 vector, similar to \code{dim()}.
#' 
#' @keywords Accessors
#' @export
kdim <- function(x)
{
  if (class(x) == "GenBandMat")
    c(x@kl, x@ku)
  else if (class(x) == "SymBandMat")
    c(x@k, x@k)
  else if (class(x) == "DiagMat")
    c(0L, 0L)
  else if (class(x) == "ZeroMat")
    c(-1L, -1L)
  else
    stop("'x' must be a band matrix")
}



# TODO
# Prefer not to export this, because someone will likely do something crazy with it
setGeneric("setData<-", 
  function(x, value) 
    standardGeneric("setData<-"), 
  package="band"
)

setMethod("setData<-", signature(x="BandMat", value="VecTypes"), 
  function(x, value)
  {
    x@Data[!is.na(x)] <- value
    invisible()
  }
)
