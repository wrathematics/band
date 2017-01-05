#' symmetrize
#' 
#' Make a matrix-like object symmetric.
#' 
#' @details
#' For a matrix input, we use a block algorithm.
#' 
#' @param x
#' A matrix-like object.
#' @param triangle
#' A single character, either "u" or "l" for upper or lower, respectively.
#' This determines which triangle is preserved.  The default is the upper
#' triangle.  Case is ignored.
#' 
#' @return
#' A matrix-like object of the same type as the input.
#' 
#' @export
symmetrize <- function(x, triangle="u") UseMethod("symmetrize", x)

symmetrize_err <- function(x, triangle="u")
{
  if (class(x) == "ZeroMat" || class(x) == "DiagMat" || class(x) == "SymMat")
    stop(paste("a", class(x), "matrix is already symmetric"))
}

#' @export
symmetrize.DiagMat <- symmetrize_err

#' @export
symmetrize.ZeroMat <- symmetrize_err

#' @export
symmetrize.SymMat <- symmetrize_err

### TODO
# #' @export
# symmetrize.GenBandMat <- function(x)
# {
#   
# }

#' @export
symmetrize.matrix <- function(x, triangle="u")
{
  if (!is.numeric(x) && !is.logical(x))
    stop("argument 'x' must contain numeric, integer, or logical data")
  
  check.is.char(triangle)
  
  triangle <- tolower(triangle)
  if (triangle != "u" && triangle != "l")
    stop("argument 'triangle' must be one of 'u' (upper) or 'l' (lower)")
  
  .Call(R_symmetrize, x, triangle)
}
