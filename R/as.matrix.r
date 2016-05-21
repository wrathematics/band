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
  
  .Call(R_tomatrix_fromband, getData(x), dim[1L], dim[2L], k[1L], k[2L])
}



asmat_SymMat <- function(x)
{
  n <- getdim(x)[1L]
  triangle <- x@triangle
  
  .Call(R_tomatrix_fromsym, getData(x), n, triangle)
}



#' as.matrix
#' 
#' @param x
#' A banded or symmetric matrix.
#' 
#' @return
#' An R matrix.
#' 
#' @keywords Casters
#' @name as.matrix
#' @rdname as.matrix
NULL

#' @rdname as.matrix
#' @export
setMethod("as.matrix", signature(x="BandMat"), asmat_BandMat)

#' @rdname as.matrix
#' @export
setMethod("as.matrix", signature(x="SymMat"), asmat_SymMat)
