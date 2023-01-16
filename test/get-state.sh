#!/bin/bash
# Usage: $0 <entity_id>

source env.sh
  
curl -X GET -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -H "Content-Type: application/json" \
     ${HA_BASE_URL}/states/$1 | python -m json.tool
