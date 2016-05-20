getData <- function(x) x@Data

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
  else stop("'x' must be a band matrix")
}
