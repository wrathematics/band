#' isSym
#' 
#' Test if a matrix is symmetric.
#' 
#' @param object
#' A matrix-like object.
#' 
#' @param ...
#' Ignored.
#' 
#' @return
#' \code{TRUE} or \code{FALSE}, accordingly.
#' 
#' @export
isSym <- function(x) useMethod("isSym")

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
