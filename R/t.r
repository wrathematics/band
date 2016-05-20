xpose_BandMat <- function(x)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  .Call(R_xposebanded, getData(x), dim[1L], dim[2L], k[1L], k[2L])
}



#' t
#' 
#' @param x
#' A banded matrix.
#' 
#' @return
#' A banded matrix of the same type.
#' 
#' @keywords LinAlg
#' @export
setMethod("t", signature(x="BandMat"), xpose_BandMat)
