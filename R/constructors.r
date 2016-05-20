#' Banded Matrix Constructors
#' 
#' Constructors for banded matrices. WARNING: for advanced users only.
#' Use the caster function for conversions.
#' 
#' @details
#' See url in the references for an explanation of the storage.
#' 
#' @param dim
#' The matrix dimension.
#' @param Data
#' The compact band matrix representation.
#' @param kl,ku
#' The lower and upper bandwidths, respectively.
#' 
#' @references \url{http://www.netlib.org/lapack/lug/node124.html}
#' @seealso \code{\link{as.banded}} and \code{\link{as.matrix}}
#' @name constructors
#' @rdname constructors
NULL

#' @rdname constructors
#' @export
zeromat <- function(dim)
{
  new("ZeroMat", dim=dim)
}

#' @rdname constructors
#' @export
diagmat <- function(Data, dim)
{
  new("DiagMat", Data=Data, dim=dim)
}

#' @rdname constructors
#' @export
genbandmat <- function(Data, dim, kl, ku)
{
  new("GenBandMat", Data=Data, dim=dim, kl=kl, ku=ku)
}
