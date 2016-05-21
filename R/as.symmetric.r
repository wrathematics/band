#' as.symmetric
#' 
#' Convert a regular R matrix into a packed symmetric matrix.
#' 
#' @details
#' The values \code{kl} and \code{ku} describe the bandwidth of the band
#' matrix.  If they are different, they will produce a general banded
#' matrix.  If they are both 0, they will produce a diagonal matris.
#' 
#' @param x
#' A matrix containing numeric, integer, or logical data.
#' @param kl,ku
#' The size of the lower and upper bands.  At least one value \code{kl} or
#' \code{ku} must be supplied; however, if one is missing, the other will
#' be assumed to be the same value. Each supplied value should be a
#' non-negative integer. See the details section for more information
#' about these values.
#' 
#' @return
#' A symmetric matrix.
#' 
#' @examples
#' x <- matrix(1:9, nrow=3)
#' 
#' # A diagonal matrix
#' as.symmetric(x)
#' 
#' @seealso \code{\link{kdim}} and \code{\link{classes}}
#' @keywords Casters
#' @export
as.symmetric <- function(x, triangle="u")
{
  if (!is.matrix(x))
    stop("argument 'x' must be a matrix")
  if (!is.numeric(x) && !is.logical(x))
    stop("argument 'x' must contain numeric, integer, or logical data")
  
  if (!is.character(triangle) || length(triangle) != 1 || nchar(triangle) != 1)
    stop("argument 'triangle' must be a single character")
  
  triangle <- tolower(triangle)
  if (triangle != "u" && triangle != "l")
    stop("argument 'triangle' must be one of 'u' for upper or 'l' for lower")
  
  out <- .Call(R_tosymmetric, x, triangle)
  
  ret <- symmat(Data=out, dim=dim(x), triangle=triangle)
  
  ret
}
