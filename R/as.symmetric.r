#' as.symmetric
#' 
#' Convert a regular R matrix into a packed symmetric matrix, whether or not
#' the input matrix was symmetric. Test for symmetry with \code{band::isSym()}
#' and NOT R's \code{isSymmetric()}.
#' 
#' @details
#' The storage scheme is packed symmetric storage, so only the diagonal and
#' the specified triangle are stored.
#' 
#' @param x
#' A matrix containing numeric, integer, or logical data.
#' @param triangle
#' A single character, either "u" or "l" for upper or lower, respectively.
#' This determines which triangle is used to create the packed storage matrix.
#' The default is the upper triangle.  Case is ignored.
#' 
#' @return
#' A symmetric matrix.
#' 
#' @examples
#' x <- matrix(1:25, nrow=5)
#' # use the upper triangle. note that 'x' is not symmetric, but the return is
#' as.symmetric(x)
#' 
#' # lower triangle
#' as.symmetric(x, 'l')
#' 
#' @references \url{http://www.netlib.org/lapack/lug/node123.html}
#' @seealso \code{\link{isSym}}, \code{\link{kdim}}, and \code{\link{classes}}
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
