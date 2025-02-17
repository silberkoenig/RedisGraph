/*
* Copyright 2018-2022 Redis Labs Ltd. and Contributors
*
* This file is available under the Redis Labs Source Available License Agreement
*/

#include "RG.h"
#include "../query_ctx.h"
#include "resultset_statistics.h"
#include <string.h>

bool ResultSetStat_IndicateModification
(
	const ResultSetStatistics *stats
) {
	ASSERT(stats != NULL);

	return (
			stats->nodes_created > 0          ||
			stats->properties_set > 0         ||
			stats->relationships_created > 0  ||
			stats->nodes_deleted > 0          ||
			stats->relationships_deleted > 0  ||
			stats->labels_added > 0           ||
			stats->indices_created > 0        ||
			stats->indices_deleted > 0
			);
}

// initialize resultset statistics
void ResultSetStat_init
(
	ResultSetStatistics *stats  // resultset statistics to initialize
)
{
	ASSERT(stats != NULL);

	memset(stats, 0, sizeof(ResultSetStatistics));

	stats->indices_created = STAT_NOT_SET;
	stats->indices_deleted = STAT_NOT_SET;
}

// emit resultset statistics
void ResultSetStat_emit
(
	RedisModuleCtx *ctx,              // redis module context
	const ResultSetStatistics *stats  // statistics to emit
) {
	int buflen;
	char buff[512] = {0};
	size_t resultset_size = 2; // execution time, cached

	// compute required space for resultset statistics
	if(stats->labels_added          > 0) resultset_size++;
	if(stats->nodes_created         > 0) resultset_size++;
	if(stats->nodes_deleted         > 0) resultset_size++;
	if(stats->properties_set        > 0) resultset_size++;
	if(stats->relationships_deleted > 0) resultset_size++;
	if(stats->relationships_created > 0) resultset_size++;

	if(stats->indices_created != STAT_NOT_SET) resultset_size++;
	if(stats->indices_deleted != STAT_NOT_SET) resultset_size++;

	RedisModule_ReplyWithArray(ctx, resultset_size);

	if(stats->labels_added > 0) {
		buflen = sprintf(buff, "Labels added: %d", stats->labels_added);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->nodes_created > 0) {
		buflen = sprintf(buff, "Nodes created: %d", stats->nodes_created);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->properties_set > 0) {
		buflen = sprintf(buff, "Properties set: %d", stats->properties_set);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->relationships_created > 0) {
		buflen = sprintf(buff, "Relationships created: %d", stats->relationships_created);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->nodes_deleted > 0) {
		buflen = sprintf(buff, "Nodes deleted: %d", stats->nodes_deleted);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->relationships_deleted > 0) {
		buflen = sprintf(buff, "Relationships deleted: %d", stats->relationships_deleted);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->indices_created != STAT_NOT_SET) {
		buflen = sprintf(buff, "Indices created: %d", stats->indices_created);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	if(stats->indices_deleted != STAT_NOT_SET) {
		buflen = sprintf(buff, "Indices deleted: %d", stats->indices_deleted);
		RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);
	}

	buflen = sprintf(buff, "Cached execution: %d", stats->cached ? 1 : 0);
	RedisModule_ReplyWithStringBuffer(ctx, (const char *)buff, buflen);

	// emit query execution time
	double t = QueryCtx_GetExecutionTime();
	buflen = sprintf(buff, "Query internal execution time: %.6f milliseconds", t);
	RedisModule_ReplyWithStringBuffer(ctx, buff, buflen);
}

void ResultSetStat_Clear(ResultSetStatistics *stats) {
	ASSERT(stats != NULL);

	stats->labels_added           =  0;
	stats->nodes_deleted          =  0;
	stats->nodes_created          =  0;
	stats->properties_set         =  0;
	stats->indices_created        =  STAT_NOT_SET;
	stats->indices_deleted        =  STAT_NOT_SET;
	stats->relationships_created  =  0;
	stats->relationships_deleted  =  0;
}
