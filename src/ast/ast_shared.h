/*
 * Copyright 2018-2022 Redis Labs Ltd. and Contributors
 *
 * This file is available under the Redis Labs Source Available License Agreement
 */

#pragma once

#include "../graph/graphcontext.h"
#include "../graph/entities/qg_node.h"
#include "../graph/entities/qg_edge.h"
#include "../arithmetic/arithmetic_expression.h"
#include "ast.h"

struct AR_ExpNode;

/* Updates to this enum require parallel updates to the
 * OpName array in arithmetic_expression_construct.c */
typedef enum {
	OP_UNKNOWN = 0,
	OP_NULL = 1,
	OP_OR = 2,
	OP_XOR = 3,
	OP_AND = 4,
	OP_NOT = 5,
	OP_EQUAL = 6,
	OP_NEQUAL = 7,
	OP_LT = 8,
	OP_GT = 9,
	OP_LE = 10,
	OP_GE = 11,
	OP_PLUS = 12,
	OP_MINUS = 13,
	OP_MULT = 14,
	OP_DIV = 15,
	OP_MOD = 16,
	OP_POW = 17,
	OP_CONTAINS = 18,
	OP_STARTSWITH = 19,
	OP_ENDSWITH = 20,
	OP_IN = 21,
	OP_IS_NULL = 22,
	OP_IS_NOT_NULL = 23,
	OP_XNOR = 24
} AST_Operator;

typedef struct {
	Attribute_ID *keys;
	struct AR_ExpNode **values;
} PropertyMap;

// Enum describing how a SET directive should treat pre-existing properties
typedef enum {
	UPDATE_UNSET   = 0,    // default, should not be encountered
	UPDATE_MERGE   = 1,    // merge new properties into existing property map
	UPDATE_REPLACE = 2,    // replace existing property map with new properties
} UPDATE_MODE;

// Key-value pair of an attribute ID and the value to be associated with it
// TODO Consider replacing contents of PropertyMap (for ops like Create) with this
typedef struct {
	Attribute_ID id;
	struct AR_ExpNode *exp;
} PropertySetCtx;

// Context describing an update expression.
typedef struct {
	PropertySetCtx *properties; // properties to set
	int record_idx;             // record offset this entity is stored at
	UPDATE_MODE mode;           // Whether the entity's property map should be updated or replaced
	const char *alias;          // Access-safe alias of the entity being updated
} EntityUpdateEvalCtx;

// Context describing a node in a CREATE or MERGE clause
typedef struct {
	int src_idx;                // source node record index
	int dest_idx;               // destination node record index
	int edge_idx;               // edge record index
	int reltypeId;              // edge relationship type id
	const char *src;            // source node alias
	const char *dest;           // destination node alias
	const char *alias;          // edge alias
	const char *relation;       // edge relationship type
	PropertyMap *properties;    // edge properties set
} EdgeCreateCtx;

// Context describing a relationship in a CREATE or MERGE clause
typedef struct {
	int node_idx;               // node record index
	int *labelsId;              // array of node labels id
	const char *alias;          // node alias
	const char **labels;        // node labels
	PropertyMap *properties;    // node properties set
} NodeCreateCtx;

AST_Operator AST_ConvertOperatorNode(const cypher_operator_t *op);

// Convert a map of properties from the AST into a set of attribute ID keys and AR_ExpNode values.
PropertyMap *PropertyMap_New(GraphContext *gc, const cypher_astnode_t *props);

// Clone NodeCreateCtx.
NodeCreateCtx NodeCreateCtx_Clone(NodeCreateCtx ctx);

// Free NodeCreateCtx.
void NodeCreateCtx_Free(NodeCreateCtx ctx);

// Clone EdgeCreateCtx.
EdgeCreateCtx EdgeCreateCtx_Clone(EdgeCreateCtx ctx);

void PropertyMap_Free(PropertyMap *map);

EntityUpdateEvalCtx *UpdateCtx_New(UPDATE_MODE mode, uint prop_count, const char *alias);
EntityUpdateEvalCtx *UpdateCtx_Clone(const EntityUpdateEvalCtx *ctx);
void UpdateCtx_SetMode(EntityUpdateEvalCtx *ctx, UPDATE_MODE mode);
void UpdateCtx_Clear(EntityUpdateEvalCtx *ctx);
void UpdateCtx_Free(EntityUpdateEvalCtx *ctx);

