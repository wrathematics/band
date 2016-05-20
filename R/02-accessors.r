getData <- function(x) x@Data

getdim <- function(x) x@dim

#' @export
kdim <- function(x)
{
  if (class(x) == "GenBandMat")
    c(x@kl, x@ku)
  else if (class(x) == "SymBandMat")
    c(x@k, x@k)
  else if (class(x) == "DiagMat")
    c(0L, 0L)
  else stop("'x' must be a band matrix")
}
