#' xpose
#' 
#' Transpose a matrix-like thing. In addition to supporting
#' the new classes, this method is slightly more efficient
#' than R's \code{t()} for matrix types.
#' 
#' @details
#' For a matrix input, we use a block algorithm.
#' 
#' @param x
#' A banded matrix.
#' 
#' @return
#' A matrix-like object of the same type as the input.
#' 
#' @keywords LinAlg
#' @export
xpose <- function(x) UseMethod("xpose", x)

xpose_err <- function(x)
{
  if (class(x) == "ZeroMat")
    nm <- "zero"
  else if (class(x) == "DiagMat")
    nm <- "diagonal"
  else if (class(x) == "SymMat")
    nm <- "symmetric"
  
  stop(paste("a", nm, "matrix is its own transpose"))
}

#' @export
xpose.BandMat <- xpose_err

#' @rdname xpose
xpose.SymMat <- xpose_err

#' @export
xpose.GenBandMat <- function(x)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  out <- .Call(R_xpose_band, getData(x), dim[1L], dim[2L], k[1L], k[2L])
  genbandmat(out, rev(dim), k[2L], k[1L])
}

#' @export
xpose.matrix <- function(x)
{
  dims <- dim(x)
  if (any(dims == 1L))
  {
    dim(x) <- rev(dims)
    return(x)
  }
  
  .Call(R_xpose_full, x)
}
