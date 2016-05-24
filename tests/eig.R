library(band)

mat <- matrix(1:100, 10)
sym <- as.symmetric(mat)

truth <- eigen(as.matrix(sym), only.values=TRUE)
test <- eig(sym, only.values=TRUE)

stopifnot(all.equal(truth, test))


truth <- eigen(as.matrix(sym))
test <- eig(sym)

tsv <- test$vectors
trv <- truth$vectors

for (i in 1:ncol(tsv))
{
  if (!isTRUE(all.equal(tsv[, i], trv[, i])))
    stopifnot(all.equal(-tsv[i], trv[i]))
}
