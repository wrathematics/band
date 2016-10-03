#' isSym
#' 
#' Test if a matrix-like object is symmetric.  In addition to supporting
#' the new classes, this method is SIGNIFICANTLY more efficient
#' than R's \code{isSymmetric()} for matrix types.
#' 
#' @details
#' For a matrix input, we use a block algorithm.
#' 
#' @param x
#' A matrix-like object.
#' 
#' @return
#' \code{TRUE} or \code{FALSE}, accordingly.
#' 
#' @export
isSym <- function(x) UseMethod("isSym", x)

dimseq <- function(x)
{
  dim <- getdim(x)
  if (dim[1L] != dim[2L])
    FALSE
  else
    TRUE
}

#' @export
isSym.DiagMat <- dimseq

#' @export
isSym.ZeroMat <- dimseq

#' @export
isSym.SymMat <- dimseq

#' @export
isSym.GenBandMat <- function(x)
{
  dims <- getdim(x)
  if (dims[1L] != dims[2L])
    return(FALSE)
  
  k <- kdim(x)
  if (k[1L] != k[2L])
    return(FALSE)
  
  .Call(R_isSym_band, getData(x), dims[1L], k[1L])
}

#' @export
isSym.matrix <- function(x)
{
  .Call(R_isSym_full, x)
}
