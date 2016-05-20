asmat_BandMat <- function(x)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  if (class(x) == "ZeroMat")
  {
    ret <- numeric(prod(dim))
    dim(ret) <- dim
    return(ret)
  }
  
  .Call(R_tomatrix, getData(x), dim[1L], dim[2L], k[1L], k[2L])
}



#' as.matrix
#' 
#' @param x
#' A banded matrix.
#' 
#' @return
#' An R matrix.
#' 
#' @keywords Casters
#' @export
setMethod("as.matrix", signature(x="BandMat"), asmat_BandMat)
