## TODO symmetric

#' @export
as.banded <- function(x, kl, ku)
{
  if (!is.numeric(x)) #TODO allow logical?
    stop("argument 'x' must be numeric")
  
  if (missing(kl) && missing(ku))
    stop("must supply at least one of 'kl' or 'ku'")
  else if (missing(kl))
    kl <- ku
  else if (missing(ku))
    ku <- kl
  
  dim <- dim(x)
  
  if (ku > dim[1L] || kl > dim[1L])
    stop("'ku' and 'kl' must each be smaller than nrow(x)")
  if (max(ku, kl) > min(dim))
    warning("banded storage schemes are only practical if kl, ku << min(dim(x))")
  
  ku <- as.integer(ku)
  kl <- as.integer(kl)
  
  out <- .Call(R_tobanded, x, kl, ku)
  ret <- new("GenBandMat", Data=out, dim=dim, kl=kl, ku=ku)
  
  ret
}
