#!/bin/bash
# Usage: $0 <control/action> <json-payload>
# where <json-payload> includes "entity_id": "myentity"
# Example: $0 button/press {"entity_id": ""}

source env.sh
  
curl -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -H "Content-Type: application/json" \
     -d "$2" \
     ${HA_BASE_URL}/services/$1 | python -m json.tool
