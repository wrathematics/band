asmat_BandMat <- function(x)
{
  dim <- getdim(x)
  k <- kdim(x)
  
  .Call(R_tomatrix, getData(x), dim[1L], dim[2L], k[1L], k[2L])
}



#' @export
setMethod("as.matrix", signature(x="BandMat"), asmat_BandMat)
